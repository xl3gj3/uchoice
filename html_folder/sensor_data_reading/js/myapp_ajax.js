(function(factory){
 window.read_data_ajax = factory({});
}
(function(read_data_ajax){
  const ajax_config = {
    api_url : '',
  };
  function ajax_load_config (url){
    ajax_config.api_url = url;
  }
  read_data_ajax.submit = function (action,data, function_name){
    console.log("in the read_data_ajax file, the data to be submited is ", data);
    let data_string = JSON.stringify(data);
    let function_title = JSON.stringify(function_name);
    console.log("function_name = " ,function_name);
    console.log("url is ", ajax_config.api_url);
    $.ajax({
      method : 'GET',
      dataType : 'json',
      url : ajax_config.api_url,
      data : { function : function_name , data : data_string},
      success : function(response) {
        if (response.status <0) {
          console.log("error");
          console.log(response.errMsg);

        }else {
          // console.log("success");
          switch (action) {
            case 0:
              console.log("construct customer order data");
              read_data.main.construct_display_page(response.data);

              break;
            case 1:
            console.log("construct product sensor data");

              read_data.main.construct_sensor_data_page(response.data);

              break;
            case 4:
            console.log("updating the name");

              read_data.main.update_name(response.data);

              break;
            default:
            // console.log("updating the name");
          }
        }
      }
    });

  }
  read_data_ajax.load = function(url){
    ajax_load_config(url);
    console.log("after loading url ajax_config is ", ajax_config);
  }
  return read_data_ajax;
}))


// (function(factory){
//  window.myApp = factory({});
// }
// (function(myApp){
//
//   return myApp;
// }))
