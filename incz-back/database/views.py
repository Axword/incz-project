from django_filters.rest_framework import DjangoFilterBackend
from rest_framework.decorators import action
from rest_framework.filters import OrderingFilter
from rest_framework.response import Response
from rest_framework.viewsets import ModelViewSet

from database.models import Cart, Measurement
from database.serializers import CartSerializer, MeasurmentSerializer, MeasurmentSerializerCreate


class CartViewSet(ModelViewSet):
    queryset = Cart.objects.all()
    serializer_class = CartSerializer
    filter_fields = '__all__'
    filter_backends = (OrderingFilter, DjangoFilterBackend)
    ordering_fields = '__all__'


class MeasurmentViewSet(ModelViewSet):
    queryset = Measurement.objects.all().order_by('-timestamp')
    filter_fields = '__all__'
    filter_backends = (OrderingFilter, DjangoFilterBackend)
    ordering_fields = '__all__'

    @action(methods=['get'], url_path='latest', url_name='latest', detail=False)
    def read_latest_measurement(self):
        instance = self.queryset.last()
        serializer = self.get_serializer(instance)
        return Response(serializer.data)

    def get_serializer_class(self):
        if self.action == 'create':
            return MeasurmentSerializerCreate
        return MeasurmentSerializer