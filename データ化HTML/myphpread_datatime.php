<?php
$mysqli = new mysqli('localhost', 'user1', '', 'test1db');
if ($mysqli->connect_error) {
    echo $mysqli->connect_error;
    exit();
} else {
    $mysqli->set_charset("utf8");
}
?>
<?php
$data =  [];

$sql = "SELECT * FROM date_and_time";
$my_id_label =  [];
if ($result = $mysqli->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        //echo $row["id"] ;
        //echo var_dump($row);
        $memo=$row['datatime']."  ".$row['memo'];
        
        //$memo=$memo+"1";
        $data += array($row["id"]=>$memo);
        //$jsonPHP = json_decode(var_dump($row));
        //var_dump($jsonPHP);
//$data = var_dump($row);
//echo "<br>"."<br>"."<br>";
    }
   
    
    $result->close();
    
}
$result = json_encode($data);

header('Content-Type: application/json; charset=utf-8');
echo json_encode($data);
//var_dump( $result );

//echo "<br>"."<br>"."<br>";

//echo var_dump($my_id_label);
//echo "Array length : ".count($my_id_label)."<br>";
//echo "配列最後のID　：　".$my_id_label[count($my_id_label)-1]
//$my_all_data["my_date_and_time"]["db_id"] = $my_id_label;
?>








