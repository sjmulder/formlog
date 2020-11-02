formlog
=======
Simple form handler. Mostly to experient with kcgi. Just writes the
form-encoded responses to a file (+IP address and time). No validation.
No guarantees. Only works on OpenBSD as-is.

Usage
-----
1. Host behind slowcgi or any CGI-compatible server.
2. Set this program as the action of a HTML form, e.g.
   `<form action="/cgi-bin/formlog.cgi">`.
3. Set `FL_DBPATH` to the filename to the file that will hold the form
   responses, e.g. `/var/db/myform.txt`.
4. Set `FL_OKPATH` to the path the user should be redirected to on
   success, e.g. `/thanks.html`.

Author
------
By Sijmen J. Mulder (<ik@sjmulder.nl>).
