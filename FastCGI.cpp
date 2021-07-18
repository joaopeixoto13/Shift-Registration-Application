#include "FastCGI.h"


const unsigned long BODY_MAX_SIZE = 100000;


long FastCGI::readBody(FCGX_Request& request, istringstream& body)
{
	unsigned long size = 0;
	char* cBody = 0;

	char* bodyLengthStr = FCGX_GetParam("CONTENT_LENGTH", request.envp);
	if (bodyLengthStr) {
		size_t end;
		size = stol(bodyLengthStr, &end, 10);
		if (!bodyLengthStr[end]) {
			if (size > BODY_MAX_SIZE)   // proteger o servico de excesso de dados
				size = BODY_MAX_SIZE;
			cBody = new char[1L + size];
			cin.read(cBody, size);
			cBody[size] = '\0';
			body = istringstream(cBody);
			size = (unsigned long)cin.gcount();
			delete[] cBody;
		}
		else {
			cerr << "can't parse \"CONTENT_LENGTH=" << bodyLengthStr << "\"\n";
			size = BODY_MAX_SIZE;
		}
	}
	else {
		cerr << "\"CONTENT_LENGTH\" is missing\n";
		size = BODY_MAX_SIZE;
	}

	return size;
}

