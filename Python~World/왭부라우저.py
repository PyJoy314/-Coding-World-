import webbrowser

print("왭브라우저에서 열 창 갯수를 입려하시오 : ")
N = int(input())
print("왭사이트 경로를 입력하세요 : ")
for i in range(N):
    W = input("")
    url = W
    webbrowser.open(url)
