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
build_view.prototype.display_page = function (){

};

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
  `;
  $(`#${this.id}`).html(this.view);
  selector.id = {
    input : ["customer_id"],
    button : ["submit"]
  }

}
