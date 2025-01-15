import xlrd
import random
readfile = xlrd.open_workbook("D:\Library_Manage_System\Library_Manage_System\src.xls");
sheet = readfile.sheet_by_index(0)
rows = sheet.nrows
cols = sheet.ncols
#rows = 2
file = open("D:\Library_Manage_System\Library_Manage_System\src.txt", "w", encoding="GB18030")
for i in range(1, rows):
    for j in range(cols):
        cell = sheet.cell_value(i, j)
        if j == 0 or j == 7: rcell = int(cell)
        else: rcell = cell
        outcell = str(rcell)
        outcell = outcell.replace('\r\n','')
        outcell = outcell.replace('\n','')
        outcell = outcell.replace('	', '')
        outcell = outcell.replace('   ', '')
        outcell = outcell.replace(' ', '')
        file.write(outcell + '\n')
    rd = random.randint(0, 15);
    file.write(str(rd) + '\n')
#readfile.close()
file.close()
