from rest_framework import serializers
from database.models import Cart, Measurement

class CartSerializer(serializers.ModelSerializer):

    class Meta:
        model = Cart
        fields = "__all__"

class MeasurmentSerializer(serializers.ModelSerializer):
    timestamp = serializers.DateTimeField(format='%Y/%m/%d  %H:%M:%S')

    class Meta:
        model = Measurement
        fields = "__all__"
