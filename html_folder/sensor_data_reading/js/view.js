function build_view (cfg){
  this.id = cfg.id;
}
build_view.prototype.main_page = function (selector){
  this.view = `<div>
  <div>
    <div class ="main_input_title">
      <span>Email: </span>
    </div>
    <div class ="main_input_field">
      <input id = "email" type="text">
    </div>
  </div>
  <div>
    <div class ="main_input_title">
      <span>Password: </span>
    </div>
    <div class ="main_input_field">
      <input id = "pw" type="text">
    </div>
  </div>
  <div>
    <button id = "log_in">Next</button>
  </div>
  </div>`;
  $(`#${this.id}`).html(this.view);
  selector.id = {
    input : ["email","pw"],
    button : ["log_in"]
  }
};
build_view.prototype.display_customer_data = function (data,selector){
  let data_content = ``;
  selector.id = {
    button : []
  };
  selector.cls = {
    button :[]
  }
  for (var i = 0; i < data.length; i++) {
    data_content += `<div>
                        <span>product name :${data[i].name} </span>
                        <span>serial id :${data[i].serial_id} </span>
                        <button class = "get_select_data" id = "product_data-${data[i].product_id}_${data[i].serial_id}">view</button>
                     </div>`;
    selector.id.button.push(`product_data-${data[i].product_id}_${data[i].serial_id}`);
  }
  selector.cls.button.push(`get_select_data`);

  $('.customer_data_holder').html(data_content);
};
build_view.prototype.sesnsor_data = function (data){
  // console.log("what kind of data we have ", data );
  let title = Object.keys(data[0]);
  let big_content = '';
  for (var i = 0; i < data.length; i++) {
    let content = "";
    for (var j = 0; j < title.length; j++) {
      content += `<span> ${title[j]}:${data[i][title[j]]} </span>`
    }
    big_content += `<div>${content}</div>`;
  }
  $('.product_data_holder').html(big_content);

}
build_view.prototype.testing_page = function (selector){
  console.log("i am loading testing page");
  this.view = `
  <div>
    <div>
      <span>
          Customer id :
      </span>
      <span>
        <select name="customer" id = "customer_id">
          <option value="1">1</option>
          <option value="2">2</option>
        </select>
      </span>
    </div>
    <div>
      <button id = "submit" class = "form-control">Submit</button>
    </div>
  </div>
  <div class = "customer_data_holder"></div>
  <div class = "product_data_holder"></div>

  `;
  $(`#${this.id}`).html(this.view);

  selector.id = {
    input : ["customer_id"],
    button : ["submit"]
  }

}
