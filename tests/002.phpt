--TEST--
wcl_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('wcl')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = wcl_test1();

var_dump($ret);
?>
--EXPECT--
The extension wcl is loaded and working!
NULL
