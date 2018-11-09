// main.js is the core js file of this app.
// view.js handel the view, gernerating  of the application
// controller is handleing the binding event (id , class)

(function(factory){
 window.read_data = factory(window.read_data);
}

(function(read_data){
  const controller = {
    input_data : {},
    bind : function (page,selector){
      switch (page) {
        case "main":

          break;
        case "data":

          break;
        default:
          console.log("testing selector event binding will be handel here");
          read_init_value(selector);

          bind_event_testing(selector);
      }
    }
  }
  function read_init_value(selector){
    controller.input_data["customer_id"] = $(`#${selector.id.input[0]}`).val();
  }
  function bind_event_testing(selector){
    console.log("selector is ", selector);
    let id = selector.id;
    console.log("the preset customer_id = ", controller.input_data["customer_id"]);
    $(`#${id.input[0]}`).change(function(){
      controller.input_data["customer_id"] = $(`#${id.input[0]}`).val();
      console.log("the customer_id = ", controller.input_data["customer_id"]);
    });
    $(`#${id.button[0]}`).click(function(){
      console.log("fire request to backend");
      read_data.submit(controller.input_data);
    });
  }
  read_data.controller = controller;
  return read_data;
}))
