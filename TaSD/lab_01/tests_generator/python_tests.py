from decimal import Decimal, getcontext

RULER_TEXT = "---------1---------2---------3---------4---------5\n"

def multiply_large_numbers(num1, num2):
    # Устанавливаем точность для округления
    getcontext().prec = 400
    
    # Преобразуем числа в объекты Decimal
    decimal_num1 = Decimal(num1)
    decimal_num2 = Decimal(num2)
    
    # Вычисляем произведение
    result = (decimal_num1 * decimal_num2)
    
    return result

# Пример использования функции
nums = input().strip().split()

num1, num2 = nums[0], nums[1]
while  num1 != "" and num2 != "":
    result = multiply_large_numbers(num1, num2)
    print(result)
    nums = input().strip().split()
    if len(nums) > 1:
        num1, num2 = nums[0], nums[1]
    else:
        break
