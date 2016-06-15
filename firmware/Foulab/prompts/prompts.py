import sys

with open(sys.argv[1], "rb") as f:
  data = f.read()

  temp = ""
  prompts = []
  for i in range(0, len(data)):
    temp += data[i]

    if (len(temp) == 20):
      prompts.append(temp)
      temp = ""

  if ((len(sys.argv) == 3) and (sys.argv[2] == "wiki")):
    print('^ Hex ^ Display ^')
    for i in range(0, len(prompts), 2):
      print('|' + ''.join(x.encode('hex') for x in prompts[i]) + ' \\\\ ' + ''.join(x.encode('hex') for x in prompts[i+1]) + '|' + prompts[i] +' \\\\ ' + prompts[i+1] + '|')
  else:
    j = 0
    for i in range(0, len(prompts)):
      print('|' + ''.join(x.encode('hex') for x in prompts[i]) + '|' + prompts[i] + '|')
      j += 1

      if (j == 2):
        print
        j = 0
