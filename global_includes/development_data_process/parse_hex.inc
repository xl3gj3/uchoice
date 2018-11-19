<?php

  class parse_hex
  {
    // variables declartion for this Object
    private $id_len;
    private $nubmer_sensors_len;
    private $name_len;
    private $data_type_len;
    private $data;
    public $response;
    private $sensors_number;
    // private $id_len;

    public function hexTo32Float($strHex) {
      $v = hexdec($strHex);
      $x = ($v & ((1 << 23) - 1)) + (1 << 23) * ($v >> 31 | 1);
      $exp = ($v >> 23 & 0xFF) - 127;
      return $x * pow(2, $exp - 23);
    }
    function __construct($data_structure)
    {
      foreach ($data_structure as $attribute => $length) {
        // assign the len of each variable to
        $this->{$attribute} = $length;
      }
    }
    public function parse_data($string){
      $this->data = str_split($string);
      // $this->obtain_id();
      $this->data = $this->obtain_id();
      // echo "Below is data after obtain id " .PHP_EOL.PHP_EOL;
      //
      // var_dump($this->data);
      $this->data = $this->obtain_number_sensors();
      // echo "the number of sensor is ".$this->sensors_number.PHP_EOL;
      // echo "Below is data after obtain_number_sensors id " .PHP_EOL.PHP_EOL;
      // $this->data = $this->parse_sensor_data();

      for ($i=0; $i < $this->sensors_number; $i++) {
        $this->data = $this->parse_sensor_data();
      }
      // var_dump( $this->data);


      return $this->response;
    }
    public function get_number_sensors(){
      return $this->sensors_number;
    }
    private function parse_sensor_data(){
      $hex_name = '';
      $str_name='';
      $data_type = '';
      $reading_data ='';
      // $dec_data_type = 0;
      $temp_data = $this->data;
      for ($i=0; $i < $this->name_len; $i++) {
        // take out the name
        $hex_name .= $this->data[$i];
        unset($temp_data[$i]);
      }
      // the name is 2 hex as a group
      $hex_name = str_split($hex_name,2);

      for ($i=0; $i < sizeof($hex_name); $i++) {
        // var_dump($hex_name[$i] );
        // 20 is space, means name is done, 00 is default name space
        if ($hex_name[$i] == "20" || $hex_name[$i] == "00") {
          break;
        }

        $str_name .= chr(hexdec($hex_name[$i]));
      }
      // echo "sensor name is $str_name". PHP_EOL;
      //  the for loop below is dealing with the data type
      $temp_data = $this->rearrange_data($temp_data);
      $this->refresh_object_data($temp_data);

      // var_dump($temp_data);
      // echo "size of data_type_len is " .sizeof($this->data_type_len).PHP_EOL;
      for ($i=0; $i < $this->data_type_len; $i++) {
        $data_type .= $this->data[$i];
        unset($temp_data[$i]);
      }
      $temp_data = $this->rearrange_data($temp_data);
      $this->refresh_object_data($temp_data);
      // $this->data = $temp_data;
      // 0 = 1 bytes, so we plus 1
      $data_type = hexdec($data_type) + 1;

      // echo "data type is $data_type". PHP_EOL;

      // # if data_type is 03, we use hexTo32Float , otherwise, we use hexdec(php preset function)
      switch ($data_type) {
        case 4:
          // code...
          // # use hexTo32Float
          for ($i=0; $i < $data_type*2; $i++) {
            $reading_data .= $this->data[$i];
            unset($temp_data[$i]);
          }
          $reading_data = $this->hexTo32Float($reading_data);
          // echo "floating ".PHP_EOL;
          // echo $reading_data .PHP_EOL;

          $this->response[$str_name] = $reading_data;
          break;

        default:
          $reading_data = hexdec($reading_data);
          $this->response[$str_name] = $reading_data;
          break;
      }

      // var_dump($name);
      //  remove the data which is parsed from the raw data
      return $this->rearrange_data($temp_data);

    }
    private function rearrange_data($temp_data){
      $return_output=[];
      foreach ($temp_data as $key => $value) {
        $return_output[] = $value;
      }
      return $return_output;
    }
    private function refresh_object_data($temp_data){
      $this->data = $temp_data;
    }
    private function obtain_number_sensors(){
      $temp_data = $this->data;
      $hex_sensor_number = "";

      for ($i=0; $i < $this->nubmer_sensors_len; $i++) {
        $hex_sensor_number .= $this->data[$i];
        // takes out the number of sensor from the data string
        unset($temp_data[$i]);
      }
      $this->sensors_number = hexdec($hex_sensor_number);
      return $this->rearrange_data($temp_data);

    }
    private function obtain_id (){
      $id = "";
      $temp_data = $this->data;
      // echo "Below is data" .PHP_EOL.PHP_EOL;
      // var_dump($this->data);

      for ($i=0; $i < $this->id_len; $i++) {
        $id .= $this->data[$i];
        unset($temp_data[$i]);
      }
      // var_dump($temp_data);
      $this->response["serial_id"] = $id;
      return $this->rearrange_data($temp_data);
    }
  }
?>
