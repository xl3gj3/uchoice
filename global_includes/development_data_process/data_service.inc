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
    $this->db->query('select serial_number.product_id,serial_number.serial_id,product_list.*,customer_info.customer_id
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
  public function get_sensor_data ($data){
    // var_dump($data);
    $table = $this->general_table_name.$data["product_id"];
    $this->db->query('SELECT * from '.$table.' where serial_id = :serial_id')
             // ->bind(":table",$table)
             ->bind(":serial_id",$data["serial_id"])
             ->execute();
    $result = $this->db->resultset();

    for ($i=0; $i < sizeof($result) ; $i++) {
      for ($j=0; $j < sizeof($this->drop_col_name); $j++) {
        unset($result[$i][$this->drop_col_name[$j]]);
      }
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
