def Chat():
    # MCAT = [] # 이 변수는 사용되지 않고 바로 덮어쓰여지므로 제거합니다.
    # CB = [] # CB는 각 메시지마다 새로 생성하여 사용합니다.
    C = {}
    CM = 0
    M = 0
    Nick = input("닉네임을 임력 : ")
    print(Nick,"님, 제 한줄노트 프로그램에 오신 걸 환영합니다~")
    print()

    while True:
        input_message = input("txt를 입력(나가려면 'exit를 임력) : ") # 'MCAT' 대신 더 명확한 변수 이름을 사용합니다.
        C[CM] = input_message

        # 제너레이터 객체 대신 실제 2진수 문자열 리스트를 생성합니다.
        binary_parts = [format(ord(char), '08b') for char in input_message]
        # 생성된 2진수 문자열 리스트를 공백으로 연결합니다.
        joined_binary_string = ' '.join(binary_parts)

        M += (len(input_message)+len(joined_binary_string))
        if input_message.lower() == 'exit':
            break
        print(f"{Nick} {M}₩/$ : {C[CM]}")
        print(f"-> 2진수 = {joined_binary_string}") # 올바르게 연결된 2진수 문자열을 출력합니다.
        CM += 1

Chat()

#🖨🖥⌨🎮💿💽💾🎼🎬💻📱🎹📀

# D:/⟪👨🏻‍💻태민파일✨⟫/파이썬 작품/Python Conway's Game of Life (pettens & python files)/Python Conway's Game of Life (pettens & python files)/Minecraft Otherside piano.mp4

#A = input().strip()
#A = list(A)
#M = 0
#S = r"[-|Minecraft BE_1.21.132v.exe&Golly.exe&https://solwitter.top/ &http://127.0.0.1:5001/ &https://github.com/PyJoy314/-Coding-World- &https://playentry.org/project/69b7bd38c0d3e18c3166ee3a &https://chatgpt.com/c/6984409f-5f88-8320-96ac-e44b0f735b8e &https://colab.research.google.com/drive/1DxI1-G8uhpxciJVNTvYLkMG5Mc-sO_ay#scrollTo=9UDbh2oIEBEk &https://conwaylife.com/ &https://playentry.org/profile/67fe212637649f1c5b0ac0f2/project?sort=created&term=all&isOpen=all &E:\⟪👨🏻‍💻태민파일✨⟫\작품모음\Joyce's movie 001.mp4&/storage/emulated/0/ 「태민작품」/「태민작품」 / 「태민작품」/Empire_Dithered_327x537 Minecraft Bedrock image (1) (1).rle &https://crispiest-crunchingly-dani.ngrok-free.dev/ &⟪大韓 Multiverse Empire • Established 1995 • 건양(建陽) 원년⟫.py &⟪大韓 Multiverse Empire • Established 1995 • 건양(建陽) 원년⟫.html &https://golly.sourceforge.io/webapp/golly.html#find  &C:\Users\JOY\Desktop\태민이 휴대폰\⟪👨🏻‍💻태민파일✨⟫\파이썬 작품\Python Conway's Game of Life (pettens & python files)\Python Conway's Game of Life (pettens & python files)\⟪大韓 Multiverse Empire • Established 1995 • 건양(建陽) 원년 314x314px StarWars logo⟫.rle &E:\⟪👨🏻‍💻태민파일✨⟫\파이썬 작품\Python Conway's Game of Life (pettens & python files)\Python Conway's Game of Life (pettens & python files)\「태민작품」\Empire_Dithered_1919x1079 Windows 11&Minecraft Bedrock image - 복사본.rle &E:\⟪👨🏻‍💻태민파일✨⟫\파이썬 작품\Python Conway's Game of Life (pettens & python files)\Python Conway's Game of Life (pettens & python files)\Python Conway's Game of Life.py &Coway's life of game &Microsoft WindowsXP Prosaser &chatapp.zip &Python_IDLE-3.14.exe &Midda &ect:-]"

#while True:
#  M += (len(A)+len(S))
#  print((f"[-:[{S}].[~]:-]=~=[-:[{M}₩$].[$]:-]" * 1995).join(A))

#이걸 복사 해보세요!(선택) --> [-|Minecraft BE_1.21.132v.exe&Golly.exe&https://solwitter.top/ &http://127.0.0.1:5001/ &https://github.com/PyJoy314/-Coding-World- &https://playentry.org/project/69b7bd38c0d3e18c3166ee3a &https://chatgpt.com/c/6984409f-5f88-8320-96ac-e44b0f735b8e &https://colab.research.google.com/drive/1DxI1-G8uhpxciJVNTvYLkMG5Mc-sO_ay#scrollTo=9UDbh2oIEBEk &https://conwaylife.com/ &https://playentry.org/profile/67fe212637649f1c5b0ac0f2/project?sort=created&term=all&isOpen=all &E:\⟪👨🏻‍💻태민파일✨⟫\작품모음\Joyce's movie 001.mp4&/storage/emulated/0/ 「태민작품」/「태민작품」 / 「태민작품」/Empire_Dithered_327x537 Minecraft Bedrock image (1) (1).rle &https://crispiest-crunchingly-dani.ngrok-free.dev/ &⟪大韓 Multiverse Empire • Established 1995 • 건양(建陽) 원년⟫.py &⟪大韓 Multiverse Empire • Established 1995 • 건양(建陽) 원년⟫.html &https://golly.sourceforge.io/webapp/golly.html#find  &C:\Users\JOY\Desktop\태민이 휴대폰\⟪👨🏻‍💻태민파일✨⟫\파이썬 작품\Python Conway's Game of Life (pettens & python files)\Python Conway's Game of Life (pettens & python files)\⟪大韓 Multiverse Empire • Established 1995 • 건양(建陽) 원년 314x314px StarWars logo⟫.rle &E:\⟪👨🏻‍💻태민파일✨⟫\파이썬 작품\Python Conway's Game of Life (pettens & python files)\Python Conway's Game of Life (pettens & python files)\「태민작품」\Empire_Dithered_1919x1079 Windows 11&Minecraft Bedrock image - 복사본.rle &E:\⟪👨🏻‍💻태민파일✨⟫\파이썬 작품\Python Conway's Game of Life (pettens & python files)\Python Conway's Game of Life (pettens & python files)\Python Conway's Game of Life.py &Coway's life of game &Microsoft WindowsXP Prosaser &chatapp.zip &Python_IDLE-3.14.exe &Midda &ect:-] <--
