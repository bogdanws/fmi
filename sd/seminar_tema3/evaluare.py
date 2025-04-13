def evaluate_expression(expression):
    operators = []
    values = []
    
    i = 0
    while i < len(expression):
        if expression[i] == ' ':
            i = i + 1
            continue
            
        if expression[i].isdigit():
            num = 0
            while i < len(expression) and expression[i].isdigit():
                num = num * 10 + int(expression[i])
                i = i + 1
            values.append(num)
            i = i - 1
            
        elif expression[i] == '(':
            operators.append(expression[i])
            
        elif expression[i] == ')':
            while len(operators) > 0 and operators[-1] != '(':
                operator = operators.pop()
                right = values.pop()
                left = values.pop()
                if operator == '+':
                    values.append(left + right)
                elif operator == '-':
                    values.append(left - right)
                elif operator == '*':
                    values.append(left * right)
                elif operator == '/':
                    values.append(left // right)
            operators.pop()
            
        elif expression[i] == '+' or expression[i] == '-' or expression[i] == '*' or expression[i] == '/':
            while len(operators) > 0 and operators[-1] != '(':
                prev_precedence = 2 if operators[-1] in ['*', '/'] else 1
                curr_precedence = 2 if expression[i] in ['*', '/'] else 1
                
                if prev_precedence >= curr_precedence:
                    operator = operators.pop()
                    right = values.pop()
                    left = values.pop()
                    if operator == '+':
                        values.append(left + right)
                    elif operator == '-':
                        values.append(left - right)
                    elif operator == '*':
                        values.append(left * right)
                    elif operator == '/':
                        values.append(left // right)
                else:
                    break
            operators.append(expression[i])
            
        i = i + 1
    
    while len(operators) > 0:
        operator = operators.pop()
        right = values.pop()
        left = values.pop()
        if operator == '+':
            values.append(left + right)
        elif operator == '-':
            values.append(left - right)
        elif operator == '*':
            values.append(left * right)
        elif operator == '/':
            values.append(left // right)
    
    return values[0]

input_file = open('evaluare.in', 'r')
expression = input_file.read().strip()
input_file.close()

result = evaluate_expression(expression)

output_file = open('evaluare.out', 'w')
output_file.write(str(result))
output_file.close()