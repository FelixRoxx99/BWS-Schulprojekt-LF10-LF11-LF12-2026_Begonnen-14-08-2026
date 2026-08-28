# Minimal testcases

1) Login
- admin/admin => success
- user/user => success
- wrong credentials => fail

2) Device CRUD
- add device => appears in list
- edit device => changes persist
- delete device (admin) => removed

3) Ausleihe/Rückgabe
- checkout available device => history entry + status Ausgeliehen
- checkout same device twice => fail
- return device => rueckgabedatum set + status Verfügbar
