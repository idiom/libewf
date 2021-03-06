#!/bin/bash
#
# Expert Witness Compression Format (EWF) library read testing script
#
# Copyright (c) 2006-2014, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this software.  If not, see <http://www.gnu.org/licenses/>.
#

EXIT_SUCCESS=0;
EXIT_FAILURE=1;
EXIT_IGNORE=77;

INPUT="input_old";

LS="ls";
TR="tr";
SED="sed";
SORT="sort";
UNIQ="uniq";
WC="wc";

test_read_chunk()
{ 
	echo "Testing read of input:" $*;

	./${EWF_TEST_READ_CHUNK} $*;

	RESULT=$?;

	echo "";

	return ${RESULT};
}

EWF_TEST_READ_CHUNK="ewf_test_read_chunk";

if ! test -x ${EWF_TEST_READ_CHUNK};
then
	EWF_TEST_READ_CHUNK="ewf_test_read_chunk.exe";
fi

if ! test -x ${EWF_TEST_READ_CHUNK};
then
	echo "Missing executable: ${EWF_TEST_READ_CHUNK}";

	exit ${EXIT_FAILURE};
fi

if ! test -d ${INPUT};
then
	echo "No ${INPUT} directory found, to test read create ${INPUT} directory and place EWF test files in directory.";
	echo "Use unique filename bases per set of EWF image file(s)."

	exit ${EXIT_IGNORE};
fi

RESULT=`${LS} ${INPUT} | ${TR} ' ' '\n' | ${SED} 's/[.][^.]*$//' | ${SORT} | ${UNIQ} | ${WC} -l`;

if test ${RESULT} -eq 0;
then
	echo "No files found in ${INPUT} directory, to test read place EWF test files in directory.";
	echo "Use unique filename bases per set of EWF image file(s)."

	exit ${EXIT_IGNORE};
fi

# Run tests for: E01, e01, s01
BASENAMES=`${LS} ${INPUT}/*.??? | ${TR} ' ' '\n' | ${SED} 's/[.][^.]*$//' | ${SORT} | ${UNIQ}`;

for BASENAME in ${BASENAMES};
do
	FILENAMES=`${LS} ${BASENAME}.??? | ${TR} '\n' ' '`;

	if ! test_read_chunk ${FILENAMES};
	then
		exit ${EXIT_FAILURE};
	fi
done

# Run tests for: Ex01
BASENAMES=`${LS} ${INPUT}/*.???? | ${TR} ' ' '\n' | ${SED} 's/[.][^.]*$//' | ${SORT} | ${UNIQ}`;

for BASENAME in ${BASENAMES};
do
	FILENAMES=`${LS} ${BASENAME}.???? | ${TR} '\n' ' '`;

	if ! test_read_chunk ${FILENAMES};
	then
		exit ${EXIT_FAILURE};
	fi
done

exit ${EXIT_SUCCESS};

