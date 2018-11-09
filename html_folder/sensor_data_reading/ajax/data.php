<?php
//include "../../includes/global.inc";
include "../../../global_config/development_data_process/data_service.inc";
include '../../../global_config/development_data_process/config.inc';
// include INCLUDE_PATH . '/JerryDatabase.class.inc';

//include '../includes/import.inc';

//include INCLUDE_PATH."/dataService.inc";
$response = array(
    'status' => 1
);
try {
    //r1Exception::requireLogin();
    if (!empty($_POST['function'])) {
      $response["test msg"] = "get request : post success";
    } else if (!empty($_GET['function'])) {
      $response["test msg"] = "get request : get success";
      $service = new data_get();
      if (!empty($_GET['data'])) $data = json_decode($_GET['data'],true);
      $response['data'] = $service->{$_GET['function']}($data);

    }
} catch (Exception $e) {
    //echo 'Caught exception: ' .  $e->getMessage() ;
    //allow overwrite on status for different level of errorDisplay
    if ($response['status'] >= 1) {
      $response['status'] = -1;
    }
    switch ($e->getMessage()) {

      case '18':
        $response['errMsg'] = "Err : Build needs 1 item set at least";
        $response['status'] = -2;
        break;
      default:
        $response['errMsg'] = "Something wrong with data you save, please try again";
        break;
    }
}
// var_dump(json_encode($response));
echo json_encode($response);

?>
