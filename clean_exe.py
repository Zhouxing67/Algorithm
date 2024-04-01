import os


def clean_exe(root_path: str = "./"):
    for path, _, files in os.walk(root_path):
        for file in files:
            filepath = os.path.join(path, file)
            # print(f'cur path : {path}')
            if filepath.endswith(".exe") or filepath.endswith(".o"):
                os.remove(filepath)
                print(filepath)


def main():
    root_path = os.getcwd()
    clean_exe(root_path=root_path)


if __name__ == "__main__":
    main()
