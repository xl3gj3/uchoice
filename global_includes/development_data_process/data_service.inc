<?php
/**
 *
 */
 require "Database.class.inc";
 require "db_helper.inc";
class data_get
{
  private $db_helper;
  private $db;
  private $general_table_name = "data_product_";
  private $drop_col_name= ["data_id","serial_id","customer_id"];

  public function get_customer_order_data($customer_info){
    // var_dump($customer_info);
    $this->db->query('select serial_number.product_id,serial_number.serial_id,serial_number.customize_name,product_list.*,customer_info.customer_id
                      from serial_number
                      inner join product_list on product_list.product_id = serial_number.product_id
                      inner join customer_info on serial_number.customer_id = customer_info.customer_id
                      where customer_info.customer_id = :customer_id;')
             ->bind(":customer_id",$customer_info["customer_id"])
             ->execute();
    $result = $this->db->resultset();
    // echo "<pre>";
    // var_dump($result);
    // echo "</pre>";
    return $result;

  }
  public function customize_product_name($data){
    $oldkey = "name";
    $newkey = "customize_name";
    $json = str_replace('"'.$oldkey.'":', '"'.$newkey.'":', json_encode($data));

    $data = json_decode($json,true);
    // var_dump($data);
    $this->db->query('UPDATE serial_number SET customize_name = :customize_name where serial_id = :serial_id')
             ->bind(':customize_name',$data[$newkey])
             ->bind(':serial_id',$data["serial_id"])
             ->execute();
    return $data;
  }
  public function get_sensor_data ($data){
    // var_dump($data);
    // $table = $this->general_table_name.$data["product_id"];
    $this->db->query('select sensor_data.*,serial_number.customize_name,serial_number.product_id,product_list.name,product_list.type,product_list.version
                      from sensor_data
                      inner join serial_number on serial_number.serial_id = sensor_data.serial_id
                      inner join product_list on product_list.product_id = serial_number.product_id
                      where serial_number.serial_id = :serial_id order by update_date desc;')
             // ->bind(":table",$table)
             ->bind(":serial_id",$data["serial_id"])
             ->execute();
    $result = $this->db->resultset();

    for ($i=0; $i < sizeof($result) ; $i++) {
      for ($j=0; $j < sizeof($this->drop_col_name); $j++) {
        unset($result[$i][$this->drop_col_name[$j]]);
      }
      $result[$i]["data"] = round($result[$i]["data"],2);
    }
    // echo "<pre>";
    // var_dump($result);
    // echo "</pre>";
    return $result;
  }
  function __construct()
  {
    $this->db_helper = new db_helper();
    $this->db = new Database();
  }
}

 ?>
