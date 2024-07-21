oringal: str
expand: str
with open("data.txt") as oringal_file:
    oringal = oringal_file.read()
with open("expand.txt") as expand_file:
    expand = expand_file.read()

if oringal == expand:
    print("二者内容一致")
else:
    print("二者内容不一致")
