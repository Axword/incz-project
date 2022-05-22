import RestObject from "./rest-object";

class Measurment extends RestObject {
  constructor({ id, ...rest }) {
    super();
    this.id = id;
    Object.assign(this, rest);
  }
}


Measurment.URL = "measurment/";
export default Measurment;
