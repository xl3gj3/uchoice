// main.js is the core js file of this app.
// view.js handel the view, gernerating  of the application
// controller is handleing the binding event (id , class)

(function(factory){
 window.read_data = factory({});
}

(function(read_data){
  const config = {
    id : "",
    ajax_url : ""
  };
  const user_input = {
    email : "",
    pw    : "",
  };
  const selector = {
    id     : {},
    cls    : {},
  }
  function load_env_para (cfg){
    config.id = cfg.id;
    config.ajax_url = cfg.ajax_url;
  }
  function construct_main_page(){
    console.log("generate main page");
    let view_generator = new build_view(config);
    view_generator.main_page(selector);
    console.log("this selector is ",selector);
  }
  // // TEMP: testing page function
  function construct_testing_page (){
    let view_generator = new build_view(config);
    view_generator.testing_page(selector);
    console.log("this testing selector is ",selector);

  }
  read_data.submit = function (data){
      read_data_ajax.submit(data);
  }
  read_data.display_customer_order = function (data){
    console.log("data be display is" ,data);


  }
  read_data.load = function (cfg){
    console.log("loading js file");
    load_env_para(cfg);
    console.log("main page the config para is ", config);
    read_data_ajax.load(config.ajax_url);
    // TEMP: testing page for backend
    construct_testing_page();
    read_data.controller.bind("testing",selector);
    // COMBAK: uncomment the construct_main_page
    // construct_main_page();
  }
  return read_data;
}))
