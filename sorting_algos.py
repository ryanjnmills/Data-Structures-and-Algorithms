import random
import time

def bubble_sort(arr, n):
    for i in range(n-1):
        for j in range(n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

def bubble_sort_improved(arr, n):
    for i in range(n-1):
        swapped = False
        for j in range(n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
                swapped = True
        if not swapped:
            break
    return arr

def selection_sort(arr, n):
    for i in range(n-1):
        min_idx = i
        for j in range(i+1, n):
            if arr[j] > arr[min_idx]:
                min_idx = j
        min_val = arr.pop(min_idx)
        arr.insert(i, min_val)
    return arr

def selection_sort_improved(arr, n):
    for i in range(n):
        min_idx = i
        for j in range(i+1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr

def insertion_sort(arr, n):
    for i in range(1,n):
        insertion_idx = i
        current_val = arr.pop(i)
        for j in range(i-1, -1, -1):
            if arr[j] > current_val:
                insertion_idx = j
        arr.insert(insertion_idx, current_val)
    return arr

def insertion_sort_improved(arr, n):
    for i in range(1,n):
        insertion_idx = i
        current_val = arr[i]
        for j in range(i-1, -1, -1):
            if arr[j] > current_val:
                arr[j+1] = arr[j]
                insertion_idx = j
            else:
                break
        arr[insertion_idx] = current_val
    return arr 

def quicksort(arr, n):
    def partition(arr, low, high):
        pivot = arr[high]
        i = low - 1
        
        for j in range(low, high):
            if arr[j] <= pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]

        arr[i+1], arr[high] = arr[high], arr[i+1]
        return i+1
    
    def quicksort_algo(arr, low=0, high=None):
        if high is None:
            high = len(arr) - 1
        if low < high:
            pivot_idx = partition(arr, low, high)
            quicksort_algo(arr, low, pivot_idx-1)
            quicksort_algo(arr, pivot_idx+1, high)
    
    quicksort_algo(arr)
    return arr

def merge_sort(arr, n):
    def merge_sort_algo(arr):
        if len(arr) <= 1:
            return arr
        mid = len(arr) // 2
        left_half = arr[:mid]
        right_half = arr[mid:]
    merge_sort_algo(arr)
    return arr

def output_arrays(arr, func_dict, SIZE):
    print('UNSORTED ARRAY')
    print(arr)
    for code, func in func_dict.items():
        dummy_arr = arr.copy()
        returned_arr = func(dummy_arr, SIZE)
        print(f'{code}: {returned_arr}')

def output_timings(arr, func_dict, repeats, SIZE):
    timing_results = {}

    for code, func in func_dict.items():
        times = []
        for _ in range(repeats):
            dummy_arr = arr.copy()
            start_time = time.time()
            func(dummy_arr, SIZE)
            elapsed_time = time.time() - start_time
            times.append(elapsed_time)
        
        if repeats == 1:
            avg_time = min_time = max_time = times[0]
        else:
            avg_time = sum(times) / repeats
            min_time = min(times)
            max_time = max(times)
        
        timing_results[code] = (avg_time, min_time, max_time)
    
    for code, (avg_t, min_t, max_t) in timing_results.items():
        if repeats == 1:
            print(f'{code}: Time:{avg_t:.6f}')
        else:
            print(f'{code}: Avg:{avg_t:.6f}, Min:{min_t:.6f}, Max:{max_t:.6f}')

def main():
    functions = {
        'BBL': bubble_sort, 
        'BBi': bubble_sort_improved,
        'SLC': selection_sort,
        'SLi': selection_sort_improved,
        'INS': insertion_sort,
        'INi': insertion_sort_improved,
        'QIK': quicksort
    }
    SIZE, MINIMUM, MAXIMUM, REPEAT = 15, 1, 100, 100
    arr = [random.randint(MINIMUM, MAXIMUM) for _ in range(SIZE)]        

    # TODO: remove outer if statement after done testing
    if True:
        if SIZE < 31:
            output_arrays(arr, functions, SIZE)
        else:
            output_timings(arr, functions, REPEAT, SIZE)

if __name__ == '__main__':
    main()