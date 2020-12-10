def Swap(a, b):
    temp = a
    a = b
    b = temp


def partition(array, start, end):
    pivot = array[start]
    low = start + 1
    high = end

    while True:
        # If the current value we're looking at is larger than the pivot
        # it's in the right place (right side of pivot) and we can move left,
        # to the next element.
        # We also need to make sure we haven't surpassed the low pointer, since that
        # indicates we have already moved all the elements to their correct side of the pivot
        while low <= high and array[high] >= pivot:
            high = high - 1

        # Opposite process of the one above
        while low <= high and array[low] <= pivot:
            low = low + 1

        # We either found a value for both high and low that is out of order
        # or low is higher than high, in which case we exit the loop
        if low <= high:
            array[low], array[high] = array[high], array[low]
            # The loop continues
        else:
            # We exit out of the loop
            break

    array[start], array[high] = array[high], array[start]

    return high


def QuickSort(array, start, end):
    if start >= end:
        return

    p = partition(array, start, end)
    QuickSort(array, start, p-1)
    QuickSort(array, p+1, end)


def DFSHelper(list, visited, vertex):
    if(visited[vertex] != 0):
        return visited[vertex]

    if(vertex == len(list)-1):
        return 1

    for i in range(vertex+1, len(list)):
        if list[i] - list[vertex] >= 1 and list[i] - list[vertex] <= 3:
            visited[vertex] += DFSHelper(list, visited, i)
        else:
            break

    return visited[vertex]

def DepthFirstSearch(list):
    visited = [0 for i in range(len(list))]

    # if needed get the print loop here

    DFSHelper(list, visited, 0)
    return visited[0]


def main():
    with open("Input.txt") as file:
        inputList = file.readlines()
    inputList = [int(i) for i in inputList]

    QuickSort(inputList, 0, len(inputList)-1)

    inputList.insert(0, 0)
    inputList.append(inputList[len(inputList)-1] + 3)

    validPossibilities = DepthFirstSearch(inputList)
    print(validPossibilities)


main()
