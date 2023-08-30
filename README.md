## setup
```bash
1. cd your-php-src/ext
2. ./ext_skel.php --ext wcl
3. write your code
```

## compile
```bash
cd cd your-php-src/ext/wcl
make clean
make
make install
```

## test
```bash
cat main.php 
# var_dump(wcl('/var/www/html/ext/main.php'));

php -d "wcl.filter_blank=0" -c your-php-install-path/php.ini main.php 
```
