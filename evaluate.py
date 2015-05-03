import sys

def main():
	fasta_file = sys.argv[1]
	repeat_file = sys.argv[2]
	f_file = open(fasta_file,"rb")
	r_file = open(repeat_file,"rb")
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
	for line in lines:
		attrs = line.split("\t")
		label = attrs[3]
		isrepeat = int(attrs[-1][:-1])
		label = label.strip("\"")
		cnt = 0
		for key in genome_map:
			genome = genomo_map[key]
			if label in genome:
				cnt += 1
		if cnt > 1 and isrepeat == 1:
			true_positive += 1
		if cnt > 1 and isrepeat = 0:
			false_positive += 1
		if cnt == 1 and isrepeat == 1:
			false_negative += 1
		if cnt == 1 and isrepeat == 0:
			true_negative += 1
	sensitivity = true_positive*1.0/(true_positive + false_negative)
	specificity = true_negative*1.0/(true_negative + false_positive)

	print "sensitivity = " + str(sensitivity)
	print "specificity = " + str(specificity)


if __name__ == "__main__":
	main()
