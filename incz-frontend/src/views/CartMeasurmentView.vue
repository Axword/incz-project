<template>
  <div class="measurement">
    <v-main class="elevation-0 mt-4 px-5 py-3">
      <v-btn class="my-3" outlined large title="Wróć" @click="back">Wróć do listy koszyków</v-btn>
      <v-data-table
        :headers="headers"
        :items="items"
        :hide-default-footer="true"
        :fetch-objects="fetchMeasurementList"
        locale="pl-PL"
        class="elevation-1"
      />
    </v-main>
  </div>
</template>

<script>
// @ is an alias to /src
import { mapState, mapActions } from "vuex";
import router from "@/router";
export default {
  name: "MeasurementTable",
  data() {
    return {
      options: {
      },
    };
  },
  methods: {
    ...mapActions(["fetchMeasurementList", "deleteMeasurement", ]),
    async deleteItem(item) {
      (await confirm("Czy na pewno chcesz usunąć koszyk?")) &&
        this.deleteMeasurement(item);
    },
    back() {
      router.push({ name: 'CartTable' });
    },
  },
  computed: {
    ...mapState({
      errors: (state) => state.measurement.errors,
      count: (state) => state.measurement.totalMeasurementsItems,
      headers: (state) => state.measurement.measurementListHeaders,
      items: (state) => state.measurement.measurementList,
      itemsPerPage: (state) => state.measurement.measurementsPerPage,
    }),
    cartId() {
      return this.$route.params.id;
  }
  },
  async created() {
    this.fetchMeasurementList({'cart_id': this.cartId});
  },
};
</script>
xx