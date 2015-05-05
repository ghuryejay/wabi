import sys
import os

def main():
	fasta_file = sys.argv[1]
	repeat_file = sys.argv[2]
	f_file = open(fasta_file,"rb")
	r_file = open(repeat_file,"rb")
	param = sys.argv[3]
	genome_map = {}
	lines = f_file.readlines()
	key = ""
	for line in lines:
		line = line[:-1]
		if line[0] == '>':
			key = line
		else:
			genome_map[key] = line
	false_positive = 0
	true_positive = 0
	true_negative = 0
	false_negative = 0
	lines = r_file.readlines()
	revcompl = lambda x: ''.join([{'A':'T','C':'G','G':'C','T':'A'}[B] for B in x][::-1])
	for line in lines:
		attrs = line.split("\t")
		label = attrs[2]
		isrepeat = int(attrs[-1][:-1])
		label = label.strip("\"")
		cnt = 0
		for key in genome_map:
			genome = genome_map[key]
			if label in genome or revcompl(label) in genome:
				cnt += 1
		if cnt > 1 and isrepeat == 1:
			true_positive += 1
		if cnt > 1 and isrepeat == 0:
			false_negative += 1
		if cnt == 1 and isrepeat == 1:
			false_positive += 1
		if cnt == 1 and isrepeat == 0:
			true_negative += 1
	
	runfile = open("runtime","rb")
	line = runfile.readline()
#	print order nodes/epsilon	runtime	true_pos	true_neg	false_pos	false_neg	
        line = line.strip("\n")
	print str(param) + "\t" + line + "\t" + str(true_positive) + "\t" + str(true_negative) + "\t" + str(false_positive) + "\t" + str(false_negative)
	os.remove("runtime")
	


if __name__ == "__main__":
	main()
