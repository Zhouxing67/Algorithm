import os


def delete_exe(rootPath: str):
    for dirpath, _, filenames in os.walk(rootPath):
        for filename in filenames:
            filePath = os.path.join(dirpath, filename)
            if filename.endswith(".exe"):
                os.remove(filePath)
                print(f"Delete file : {filename}")


rootPath = os.getcwd()

if __name__ == "__main__":
    delete_exe(rootPath)
