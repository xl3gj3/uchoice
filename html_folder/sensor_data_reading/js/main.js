
(function(factory){
 window.read_data = factory({});
}

(function(read_data){
  const main_function = {
    submit : function (action_flag,data,function_name){
        read_data_ajax.submit(action_flag,data,function_name);
    },
    update_name : function (data){
        console.log("the data after update name is ", data);
        $('#display_name-'+data.serial_id).html("Name : "+ data.customize_name);

    },
    construct_sensor_data_page : function (data){
      init_selector();
      let view_generator = new build_view(config);
      view_generator.sesnsor_data(data);
      console.log("this testing selector is ",selector);
    },
    construct_display_page : function (data){
      init_selector();
      console.log("data be display is" ,data);
      let view_generator = new build_view(config);
      view_generator.display_customer_data(data,selector);
      console.log("this data selector is ",selector);
      read_data.controller.bind("display_data",selector);
    },
    load : function (cfg){
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
  };
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
    init_selector();
    let view_generator = new build_view(config);
    view_generator.testing_page(selector);
    console.log("this testing selector is ",selector);

  }
  // read_data.main_submit = function (action_flag,data,function_name){
  //     read_data_ajax.submit(action_flag,data,function_name);
  // }
  function init_selector(){
    selector.id = {};
    selector.cls = {};
  }
  read_data.main = main_function;
  return read_data;
}))
