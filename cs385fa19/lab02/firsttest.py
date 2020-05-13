import unittest

class OurFirstTest(unittest.TestCase):

    def test_true(self):
        self.assertTrue(True)

    def test_false(self):
        self.assertFalse(False)

    def test_zero_division_exception(self):
        with self.assertRaises(ZeroDivisionError):
            x = 1 / 0

    def test_will_never_pass(self):
        self.assertEqual(0,1)
        
