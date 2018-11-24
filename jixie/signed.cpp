/*调用腾讯云接口的签名算法*/


#include <stdio.h>  
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <openssl/opensslconf.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>  
#include <openssl/pem.h>
#include <openssl/bio.h>
#include "sha1.h"
#include "md5.h"
#include <string>
#include <vector>
#include <sstream>

#define HMAC_LENGTH 20

std::vector<unsigned char> hmac_sha1(std::string& data, std::string& key)
{
	unsigned char* result;
	unsigned int len = HMAC_LENGTH;

	result = (unsigned char*)malloc(sizeof(char) * len);

	HMAC_CTX  ctx;
	HMAC_CTX_init(&ctx);

	HMAC_Init_ex(&ctx, key.c_str(), key.length(), EVP_sha1(), NULL);
	HMAC_Update(&ctx, (unsigned char*)data.c_str(), data.length());
	HMAC_Final(&ctx, result, &len);
	HMAC_CTX_cleanup(&ctx);

	std::vector<unsigned char> sha1;
	for (int i = 0; i < len; i++) {
		sha1.push_back(result[i]);
	}

	free(result);
	return sha1;
}

std::string base64_encode(const std::string& src) {
	BUF_MEM * bptr = NULL;
	BIO* b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	BIO* bmem = BIO_new(BIO_s_mem());
	if (NULL == b64 || NULL == bmem) {
		return "";
	}

	bmem = BIO_push(b64, bmem);
	int ret = BIO_write(bmem, src.data(), src.length());
	if (ret <= 0) {
		return "";
	}

	ret = BIO_flush(bmem);
	BIO_get_mem_ptr(bmem, &bptr);
	std::string res(bptr->data, bptr->length);
	BIO_free_all(bmem);
	return res;

}


 std::string do_signed() {

	std::string appid = "1253112332";
	std::string secret_id = "AKIDf9ON6Zvpb6LK2bEwxjETTDhurYy8Me06";
	std::string secret_key = "3sSmpb8PPBhwwhBPN5XkiRyGI6fz4vXu";
	time_t now = time(NULL);
	long expired = (long)now + 2592000;
	long onceExpired = 0;
	long current = (long)now;
	int rdm = rand();
	std::string userid = "0";


	char buffer[41];


	std::stringstream raw_stream;
	raw_stream << "a=" << appid << "&k=" << secret_id << "&e=" << expired << "&t=" << current
		<< "&r=" << rdm;
	std::string raw = raw_stream.str();

	std::vector<unsigned char> sha1 = hmac_sha1(raw, secret_key);

	std::stringstream data_stream;
	for (int i = 0; i != sha1.size(); i++)
		data_stream << sha1[i];
	data_stream << raw;
	std::string data = data_stream.str();

	std::string sign = base64_encode(data);

	//printf("%s\n", sign.c_str());

	return sign.c_str();
}