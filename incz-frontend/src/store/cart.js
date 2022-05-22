import Cart from "../service/cart";

const state = {
  totalCartsItems: 0,
  cartList: [],
  cartDetails: {},
  errors: {},
  cartListHeaders: [
    {
      text: "Id",
      value: "id",
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
  cartsPerPage: 5,
};

const getters = {
  getCart(state) {
    return state.cartList;
  },
  getCartDetails(state) {
    return state.cartDetails;
  },
  getCartCount(state) {
    return state.totalItems;
  },
  getCartErrors(state) {
    return state.errors;
  },
  getCartListHeaders(state) {
    return state.cartListHeaders;
  },
  getCartItemsPerPage(state) {
    return state.itemsPerPage;
  },
  getCartChoices(state) {
    return state.cartChoices;
  },
  getSelectedCart(state) {
    return state.selectedCart;
  },
};

const mutations = {
  setCart(state, payload) {
    state.totalCartsItems = payload.count;
    state.cartList = [ ...payload ];
  },
  setCartDetails(state, payload) {
    state.cartDetails = { ...payload };
  },
  setCartErrors(state, payload) {
    state.errors = { ...payload };
  },
  setCartItemsPerPage(state, value) {
    console.log("DZIALA?")
    state.cartsPerPage = value;
  },
  setCartDetailsProp(state, { prop, value }) {
    state.cartDetails = { ...state.cartDetails, [prop]: value };
    state.errors = { ...state.errors, [prop]: null };
  },
  setCartChoices(state, payload) {
    state.cartChoices = [... payload];
    state.cartNamesMap = { ...payload.reduce((acc, val) => (acc[val.id] = val.name, acc), {}) };
  },
  setSelectedPracownik(state, value) {
    state.selectedPracownik = { ...value };
  },
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
  async fetchCartDetails(context, id) {
    try {
      if (!id) {
        context.commit('setCartDetails', {});
        return;
      }
      let cart = await Cart.get(id)
      context.commit('setCartDetails', cart);
      return cart;
    } catch (error) {
      return false;
    }
  },
  async createCart(context, cartId) {
    const success_message = cartId ? 'Pracownik został zaktualizowanay.': 'Pracownik został utworzony.';
    try {
      const item = await new Cart(context.state.cartDetails).save();
      context.commit('setCartDetails', item);
      context.commit('setCartErrors', {});
      context.commit('showMessage', { message: success_message });
      return true;
    } catch (error) {
      context.commit('setCartErrors', error);
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
  async updateStatusCart(context, payload) {
    try {
      await new Cart(payload).save();
      context.commit('showMessage', { message: "Pracownik został zwolniony. Data zwolnienia została ustawiona na dzisiejszą"});
    } catch(error) {
      return false
    }
  }
};


export default {
  state,
  getters,
  mutations,
  actions
};
