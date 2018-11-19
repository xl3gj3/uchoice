// main.js is the core js file of this app.
// view.js handel the view, gernerating  of the application
// controller is handleing the binding event (id , class)

(function(factory){
 window.read_data = factory(window.read_data);
}

(function(read_data){
  const controller = {
    data_from_user : {},
    bind : function (page,selector){
      controller.data_from_user = {};
      switch (page) {
        case "main":

          break;
        case "display_data":
          bind_event_display_data(selector);
          break;
        default:
          // console.log("testing selector event binding will be handel here");
          read_init_value(selector);

          bind_event_testing(selector);
      }
    }
  }
  function bind_event_display_data(selector){
    $(`.${selector.cls.button[0]}`).click(function(){
      let selected_id = $(this).attr('id');
      // selected_id is  product_data-1_1 first number is product id, second number is serial id
      console.log("selected_id is " ,selected_id);
      // console.log("the view button is click");
      let temp_var = selected_id.split(/\s*\-\s*/g);
      temp_var = temp_var[1].split(/\s*\_\s*/g);
      // console.log("the temp_var = ",temp_var);
      // controller.data_from_user["product_id"] = temp_var[0];
      controller.data_from_user["serial_id"] = temp_var[1];
      // console.log(controller.data_from_user);
      // read_data.main_submit(1,controller.data_from_user,"get_sensor_data");
      read_data.main.submit(1,controller.data_from_user,"get_sensor_data");
    })
    $(`.${selector.cls.button[1]}`).click(function(){
      let selected_id = $(this).attr('id');
      let temp_var = selected_id.split(/\s*\-\s*/g);
      // temp_var = temp_var[1].split(/\s*\_\s*/g);
      console.log("the temp_var = ",temp_var[1]);
      let update_name = $('#update_name-'+temp_var[1]).val();
      console.log("update name is ",update_name);
      controller.data_from_user["name"] = update_name;
      controller.data_from_user["serial_id"] = temp_var[1];

      read_data.main.submit(4,controller.data_from_user,"customize_product_name");


    });
  }
  function read_init_value(selector){
    controller.data_from_user["customer_id"] = $(`#${selector.id.input[0]}`).val();
  }
  function bind_event_testing(selector){
    console.log("selector is ", selector);
    let id = selector.id;
    console.log("the preset customer_id = ", controller.data_from_user["customer_id"]);
    $(`#${id.input[0]}`).change(function(){
      controller.data_from_user["customer_id"] = $(`#${id.input[0]}`).val();
      console.log("the customer_id = ", controller.data_from_user["customer_id"]);
    });
    $(`#${id.button[0]}`).click(function(){
      console.log("fire request to backend");
      read_data.main.submit(0,controller.data_from_user,"get_customer_order_data");

      // read_data.main_submit(0,controller.data_from_user,"get_customer_order_data");
    });
  }
  read_data.controller = controller;
  return read_data;
}))
