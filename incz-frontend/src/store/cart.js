import Cart from "../service/cart";

const state = {
  cartList: [],
  cartId: [],
  cartDetails: {},
  errors: {},
  cartListHeaders: [
    {
      text: "Nazwa",
      value: "name",
    },
    {
      text: "Waga",
      value: "size",
    },
    {
      text: "Akcje",
      value: "actions",
      sortable: false,
    },
  ],
};


const mutations = {
  setCart(state, payload) {
    state.cartList = [ ...payload ];
  },
  setCartDetails(state, payload) {
    state.cartDetails = { ...payload };
  },
  setCartErrors(state, payload) {
    state.errors = { ...payload };
  },
  setCartId(state, payload) {
    state.cartId = payload
  }
};

const actions = {
  async fetchCartList(context, params) {
    try {
      context.commit('setCart', await Cart.list(params));
      return true;
    } catch (error) {
      return false;
    }
  },
  async fetchCart(context, params) {
    try {
      context.commit('setCartDetails', await Cart.get(params));
      return true;
    } catch (error) {
      return false;
    }
  },
  async deleteCart(context, payload) {
    try {
      await new Cart(payload).remove();
      return true;
    } catch (error) {
      return false;
    }
  },
};


export default {
  state,
  mutations,
  actions
};
