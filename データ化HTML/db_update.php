<?php

$item = $_POST['item'];
//echo($item);
$item2 = $_POST['item2'];
//echo($item);
$mysqli = new mysqli('localhost', 'user1', '', 'test1db');

if( $mysqli->connect_errno ) {
	echo $mysqli->connect_errno . ' : ' . $mysqli->connect_error;
}

$mysqli->set_charset('utf8');

// 現在の日付を取得
$date = date('Y-m-d H:i:s');

// UPDATEのSQL作成
$sql = "UPDATE date_and_time SET
	memo='$item'
    WHERE id = '$item2'";

// SQL実行
$res = $mysqli->query($sql);

var_dump($res);
$mysqli->close();
?>
