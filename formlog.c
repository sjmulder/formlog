#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <err.h>
#include <kcgi.h>

int
main(int argc, char **argv)
{
	char *dbpath, *okpath;
	FILE *db;
	struct kreq req;
	struct kpair *pair;
	time_t rtime;
	struct tm *ltime;
	char timestr[64], *encval;
	size_t i;
	int fst=1;

	if (!(dbpath = getenv("FL_DBPATH")))
		errx(1, "no FL_DBPATH");
	if (!(okpath = getenv("FL_OKPATH")))
		errx(1, "no FL_OKPATH");

	if (!(db = fopen(dbpath, "a")))
		err(1, "fopen(%s)", dbpath);

	if (pledge("proc stdio rpath recvfd unix sendfd", NULL) == -1)
		err(1, "pledge");

	if (khttp_parse(&req, NULL, 0, NULL, 0, 0) != KCGI_OK)
		errx(1, "kcgi_parse failed");

	time(&rtime);
	ltime = localtime(&rtime);
	strftime(timestr, sizeof(timestr), "%F %T", ltime);
	fprintf(db, "%s %s ", timestr, req.remote);

	for (i=0; i < req.fieldsz; i++) {
		pair = &req.fields[i];
		if (!(encval = khttp_urlencode(pair->val)))
			errx(1, "khttp_urlencode failed");
		fprintf(db, "%s%s=%s", fst?"":"&", pair->key, encval);
		fst = 0;
		free(encval);
	}

	fputs("\n", db);
	fclose(db);

	khttp_head(&req, kresps[KRESP_STATUS], "%s", khttps[KHTTP_303]);
	khttp_head(&req, kresps[KRESP_LOCATION], "%s", okpath);
	khttp_body(&req);
	khttp_free(&req);

	return 0;
}
