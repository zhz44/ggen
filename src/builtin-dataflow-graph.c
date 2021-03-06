/* Copyright Swann Perarnau 2009
*
*   contact : Swann.Perarnau@imag.fr
*
* This software is a computer program whose purpose is to help the
* random generation of graph structures and adding various properties
* on those structures.
*
* This software is governed by the CeCILL  license under French law and
* abiding by the rules of distribution of free software.  You can  use,
* modify and/ or redistribute the software under the terms of the CeCILL
* license as circulated by CEA, CNRS and INRIA at the following URL
* "http://www.cecill.info".
*
* As a counterpart to the access to the source code and  rights to copy,
* modify and redistribute granted by the license, users are provided only
* with a limited warranty  and the software's author,  the holder of the
* economic rights,  and the successive licensors  have only  limited
* liability.
*
* In this respect, the user's attention is drawn to the risks associated
* with loading,  using,  modifying and/or developing or reproducing the
* software by the user in light of its specific status of free software,
* that may mean  that it is complicated to manipulate,  and  that  also
* therefore means  that it is reserved for developers  and  experienced
* professionals having in-depth computer knowledge. Users are therefore
* encouraged to load and test the software's suitability as regards their
* requirements in conditions enabling the security of their systems and/or
* data to be ensured and,  more generally, to use and operate it in the
* same conditions as regards security.
*
* The fact that you are presently reading this means that you have had
* knowledge of the CeCILL license and that you accept its terms.
*/

/* GGen is a random graph generator :
* it provides means to generate a graph following a
* collection of methods found in the litterature.
*
* This is a research project founded by the MOAIS Team,
* INRIA, Grenoble Universities.
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <inttypes.h>
#include <string.h>

#include "builtin.h"
#include "ggen.h"
#include "utils.h"

/* cmd declarations, we need this to be able to declare
 * the general struct
 */
static int cmd_cholesky(int argc, char** argv);
static int cmd_denselu(int argc, char** argv);
static int cmd_poisson2d(int argc, char** argv);
static int cmd_sparselu(int argc, char** argv);

/* help strings, there is a lot of them */
const char* help_dataflow[] = {
	"Methods:\n",
	"cholesky                     : block cholesky factorization\n",
	"denselu                      : dense LU decomposition\n",
	"poisson2d                    : poisson solving in 2D \n",
	"sparselu                     : sparse LU decomposition\n",
	NULL
};

static const char* cholesky_help[] = {
	"\nCholesky:\n",
	"Block Cholesky factorization.\n",
	"Arguments:\n",
	"     - n                     : size of matrix in blocks\n",
	NULL
};

static const char* denselu_help[] = {
	"\nDense LU:\n",
	"Parallel LU decomposition over a dense matrix.\n",
	"Arguments:\n",
	"     - size                  : size of one side of the matrix in blocks\n",
	NULL
};

static const char* poisson2d_help[] = {
	"\nPoisson 2D:\n",
	"A few iterations of Poisson equation solving over even grid of size n*n.\n",
	"Arguments:\n",
	"     - n                     : size of the grid\n",
	"     - iter                  : number of iterations\n",
	NULL
};

static const char* sparselu_help[] = {
	"\nSparse LU:\n",
	"Parallel LU decomposition over sparse matrix.\n",
	"Arguments:\n",
	"     - size                  : size of one side of the matrix in blocks\n",
	NULL
};

struct second_lvl_cmd cmds_dataflow[] = {
	{ "cholesky" , 1, cholesky_help , cmd_cholesky  },
	{ "denselu"  , 1, denselu_help  , cmd_denselu   },
	{ "poisson2d", 2, poisson2d_help, cmd_poisson2d },
	{ "sparselu" , 1, sparselu_help , cmd_sparselu  },
	{ 0, 0, 0, 0},
};

static int cmd_cholesky(int argc, char** argv)
{
	int err = 0;
	unsigned long n;

	err = s2ul(argv[0],&n);
	if(err) goto ret;

	g_p = ggen_generate_cholesky(n);
	if(g_p == NULL)
	{
		error("ggen error: %s\n",ggen_error_strerror());
		err = 1;
	}
ret:
	return err;
}

static int cmd_denselu(int argc, char** argv)
{
	int err = 0;
	unsigned long size;

	err = s2ul(argv[0],&size);
	if(err) goto ret;

	g_p = ggen_generate_denselu(size);
	if(g_p == NULL)
	{
		error("ggen error: %s\n",ggen_error_strerror());
		err = 1;
	}
ret:
	return err;
}

static int cmd_poisson2d(int argc, char** argv)
{
	int err = 0;
	unsigned long n,iter;

	err = s2ul(argv[0],&n);
	if(err) goto ret;

	err = s2ul(argv[1],&iter);
	if(err) goto ret;

	g_p = ggen_generate_poisson2d(n, iter);
	if(g_p == NULL)
	{
		error("ggen error: %s\n",ggen_error_strerror());
		err = 1;
	}
ret:
	return err;
}

static int cmd_sparselu(int argc, char** argv)
{
	int err = 0;
	unsigned long size;

	err = s2ul(argv[0],&size);
	if(err) goto ret;

	g_p = ggen_generate_sparselu(size);
	if(g_p == NULL)
	{
		error("ggen error: %s\n",ggen_error_strerror());
		err = 1;
	}
ret:
	return err;
}
