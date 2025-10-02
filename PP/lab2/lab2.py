from mpi4py import MPI
import numpy as np
import math

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

# --- Параметры задачи ---
N = 32768
eps = 1e-5

# --- Разделяем работу ---
counts = [N // size + (1 if i < N % size else 0) for i in range(size)]
displs = [sum(counts[:i]) for i in range(size)]
part_n = counts[rank]

# --- Вспомогательные функции ---
def dot_product(v1, v2):
    local_sum = np.dot(v1, v2)
    return comm.allreduce(local_sum, op=MPI.SUM)

def vector_norm(v):
    return math.sqrt(dot_product(v, v))

def async_matvec(A_part, x):
    local_result = A_part @ x
    global_result = np.empty(N, dtype='d')
    comm.Allgatherv([local_result, MPI.DOUBLE], [global_result, counts, displs, MPI.DOUBLE])
    return global_result

def subtract_vectors(v1, v2):
    local_diff = v1[displs[rank]:displs[rank]+part_n] - v2[displs[rank]:displs[rank]+part_n]
    global_diff = np.empty(N, dtype='d')
    comm.Allgatherv([local_diff, MPI.DOUBLE], [global_diff, counts, displs, MPI.DOUBLE])
    return global_diff

def min_residual_method(A_part, x, b):
    while True:
        r = subtract_vectors(async_matvec(A_part, x), b)
        if vector_norm(r) / vector_norm(b) < eps:
            break
        Ar = async_matvec(A_part, r)
        t = dot_product(r, Ar) / dot_product(Ar, Ar)
        x -= t * r
    return x

def generate_test_matrix():
    A_part = np.ones((part_n, N), dtype='d')
    for i in range(part_n):
        A_part[i, displs[rank] + i] = 2.0
    return A_part

# --- Основной запуск ---
def run_solver():
    A_part = generate_test_matrix()
    b = np.full(N, N + 1.0, dtype='d')
    x = np.zeros(N, dtype='d')

    comm.Barrier()
    start_time = MPI.Wtime()
    x = min_residual_method(A_part, x, b)
    comm.Barrier()
    end_time = MPI.Wtime()

    if rank == 0:
        # Добавляем результат в один файл answer.txt
        with open("answer.txt", "a") as f:
            f.write(f"{size} - {end_time - start_time:.5f}\n")
        print(f"Время работы на {size} процессах: {end_time - start_time:.2f} секунд")

if __name__ == "__main__":
    run_solver()
