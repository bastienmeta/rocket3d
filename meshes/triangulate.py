import sys
import os

# USAGE : python3 triangulate.off quads.off tris.off

out_firstline = ""
out_vertices = []
out_faces = []

if __name__ == "__main__":
	with open(sys.argv[1]) as file:
		for n, line in enumerate(file):
			if n == 0:
				in_firstline = line.split()
				out_nbv = int(in_firstline[1])
				out_nbf = 0
			elif n < out_nbv + 1:
				out_vertices.append(line)
			else:
				splitted = line.split()
				nb_vertices = int(splitted[0])

				if nb_vertices > 3:
					first_v = splitted[1]		
					for i in range(2, nb_vertices):
						prev_v = splitted[i]
						curr_v = splitted[i+1]
						out_faces.append("3 %s %s %s\n" % (first_v, prev_v, curr_v))
						out_nbf += 1
				else:
					out_nbf += 1
					out_faces.append(line)

		out_firstline = "OFF %s %s 0\n" % (out_nbv, out_nbf)

	with open(sys.argv[2], 'w') as file:
		file.write(out_firstline)
		for s in out_vertices:
			file.write(s)
		for s in out_faces:
			file.write(s)