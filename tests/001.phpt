--TEST--
Check if wcl is loaded
--SKIPIF--
<?php
if (!extension_loaded('wcl')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "wcl" is available';
?>
--EXPECT--
The extension "wcl" is available
