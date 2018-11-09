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
  read_data_ajax.submit = function (data){
    console.log("in the read_data_ajax file, the data to be submited is ", data);
    let data_string = JSON.stringify(data);
    console.log("url is ", ajax_config.api_url);
    $.ajax({
      method : 'GET',
      dataType : 'json',
      url : ajax_config.api_url,
      data : { function : 'get_customer_order_data', data : data_string },
      success : function(response) {
        if (response.status <0) {
          console.log("error happend and handleing");

        }else {
          console.log("success");
          read_data.display_customer_order(response.data);
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
