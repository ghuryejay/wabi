import sys

def main():
	fasta_file = sys.argv[1]
	repeat_file = sys.argv[2]
	f_file = open(fasta_file,"rb")
	r_file = open(repeat_file,"rb")
	genome_map = {}
	repeat_map = {}
	lines = f_file.readlines()
	key = ""
	for line in lines:
		line = line[:-1]
		if line[0] == '>':
			key = line
		else:
			genome_map[key] = line
	
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
		repeat_map[label] = cnt
	
	
    ofile = open(sys.argv[3],"rb")
    for key in repeat_map:
    	ofile.write(str(key)+"\t"+str(repeat_map[key])+"\n")
	


if __name__ == "__main__":
	main()
