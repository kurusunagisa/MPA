import subprocess

f = open("check.txt", 'r')
for _ in range(int(subprocess.check_output(['wc', '-l', 'check.txt']).decode().split(' ')[0]) // 2):
  integer = f.readline()
  multiprefix = f.readline()
  assert(integer == multiprefix)
print("success!!")
print(integer)
