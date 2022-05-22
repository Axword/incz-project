import RestObject from "./rest-object";

class Cart extends RestObject {
  constructor({ id, ...rest }) {
    super();
    this.id = id;
    Object.assign(this, rest);
  }
}

Cart.URL = "cart/";

export default Cart;
