input_f = open("input.txt", "r")
output_f = open("normalized_output.txt", "r")
table_f = open("table.txt", "w")

input_str = input_f.readline().replace("\n","")
output_str = output_f.readline().replace("\n","")
while input_str != "":
    table_f.write("|{}|{}|\n".format(input_str, output_str))
    input_str = input_f.readline().replace("\n","")
    output_str = output_f.readline().replace("\n","")
