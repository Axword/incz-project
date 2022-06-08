#!/usr/bin/env python
"""Django's command-line utility for administrative tasks."""
import os
import sys
from mqqt.fakeCarts import run as run_fake
from mqqt.subscriber import run as run_real
import threading

def main():
    os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'incz.settings')
    try:
        from django.core.management import execute_from_command_line
    except ImportError as exc:
        raise ImportError(
            "Couldn't import Django. Are you sure it's installed and "
            "available on your PYTHONPATH environment variable? Did you "
            "forget to activate a virtual environment?"
        ) from exc
    execute_from_command_line(sys.argv)


if __name__ == '__main__':
    if 'runserver' in str(sys.argv):
        #threading.Thread(target=run_fake).start()
        threading.Thread(target=run_real).start()
    main()
