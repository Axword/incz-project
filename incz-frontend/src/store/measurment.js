import Measurement from "../service/measurement";

const state = {
  measurementList: [],
  errors: {},
  measurementListHeaders: [
    {
      text: "Data pomiaru",
      value: "timestamp",
    },
    {
      text: "Wartość całkowita przyśpieszenia",
      value: "measure_acceleration_total_vector",
    },
    {
      text: "Prędkości kątowej osi Y",
      value: "measure_angle_pitch",
    },
    {
      text: "Prędkość osi Y",
      value: "measure_acceleration_pitch",
    },
    {
      text: "Prędkości kątowej osi Z",
      value: "measure_angle_yaw",
    },
    {
      text: "Prędkości osi Z",
      value: "measure_acceleration_yaw",
    },
    {
      text: "Moc sygnału odbiornika jeden",
      value: "measure_reciver_one_rx",
    },
    {
      text: "Moc sygnału odbiornika dwa",
      value: "measure_reciver_two_rx",
    },
  ],
};

const mutations = {
  setMeasurementList(state, payload) {
    state.measurementList = [...payload];
  },
  setMeasurementsItemsPerPage(state, payload) {
    state.measurementsPerPage = payload;
  },
};
const actions = {
  async fetchMeasurementList(context, params) {
    context.commit("setMeasurementList", await Measurement.list(params));
  },

  async deleteMeasurement({ commit }, payload) {
    await new Measurement(payload).remove();
    commit("showMessage", "Koszyk został pomyślnie usunięty.");
  },
};

export default {
  state,
  mutations,
  actions,
};
