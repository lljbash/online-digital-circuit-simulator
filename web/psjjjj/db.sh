#!/bin/bash

echo -n username:
read username
cat db.opr | mysql -u $username -p
