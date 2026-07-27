#import sys
#sys.stdin("input.txt", "r",encoding="UTF-8")
#sys.outdin("output.txt", "w",encoding="UTF-8")

def Chat():
    # MCAT = [] # 이 변수는 사용되지 않고 바로 덮어쓰여지므로 제거합니다.
    # CB = [] # CB는 각 메시지마다 새로 생성하여 사용합니다.
    C = {}
    CM = 0
    M = 0
    
    Nick = input("input the Nickname : ")
    print(Nick,"user, Welcome to My notepad&binary string change program~")
    print()

    while True:    
        input_message = input("input the txt(when want to exit, input the 'exit') : ") # 'MCAT' 대신 더 명확한 변수 이름을 사용합니다.
        C[CM] = input_message

        # 제너레이터 객체 대신 실제 2진수 문자열 리스트를 생성합니다.
        binary_parts = [format(ord(char), '08b') for char in input_message]
        # 생성된 2진수 문자열 리스트를 공백으로 연결합니다.
        joined_binary_string = ' '.join(binary_parts)

        M += (len(input_message)+len(joined_binary_string))
        if input_message.lower() == 'exit':
            break
#        sys.outdin(write(f"{Nick} {M}₩/$ : {C[CM]}\n"))
#        sys.outdin(write(f"-> 2진수 = {joined_binary_string}\n"))
        print(f"{Nick} {M}₩/$ : {C[CM]}")
        print(f"-> change to binary string = {joined_binary_string}") # 올바르게 연결된 2진수 문자열을 출력합니다.
        CM += 1

Chat()
