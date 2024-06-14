import numpy as np

from try_pybind11 import add_1, add_2, add_3, magic_number, magic_word, get_range_list, replace_list_value_1, replace_list_value_2, MyList, array_sum


print(f'add1(1, 2) = {add_1(1, 2)}')
print(f'add2(x=2, y=3) = {add_2(x=2, y=3)}')
print(f'add3() = {add_3()}')
print(f'magic_number = {magic_number}')
print(f'magic_word = {magic_word}')
print(f'get_range_list(10) = {get_range_list(10)}')

list = [1, 2, 3]
replace_list_value_1(list, 1, 4)

print(f'list = {list}')

list_1 = [1, 2, 3]
list_2 = replace_list_value_2(list_1, 1, 4)

print(f'list_1 = {list_1}')
print(f'list_2 = {list_2}')

my_list = MyList(10)
my_list.replace_value(1, 10)

print(f'my_list.vector = {my_list.vector}')

array = np.reshape(
    np.arange(12),
    (4, 3)
)

print(f'array_sum(array) = {array_sum(array)}')
