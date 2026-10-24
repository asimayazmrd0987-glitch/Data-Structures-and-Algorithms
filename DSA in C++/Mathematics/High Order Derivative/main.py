import tkinter as tk
from tkinter import ttk, scrolledtext, messagebox
import threading
from io import StringIO
from decimal import Decimal

import sympy as sp
from sympy.parsing.sympy_parser import (
    parse_expr,
    standard_transformations,
    implicit_multiplication_application,
    convert_xor,
)

# ------------------------------------------------------------------
# Settings
# ------------------------------------------------------------------
PRECISION = 80

# Main variables
x, y = sp.symbols("x y")

# Allowed names in the expression
LOCAL_DICT = {
    "x": x,
    "y": y,
    "e": sp.E,
    "pi": sp.pi,
    "ln": sp.log,
    "log": sp.log,
    "sin": sp.sin,
    "cos": sp.cos,
    "tan": sp.tan,
    "asin": sp.asin,
    "acos": sp.acos,
    "atan": sp.atan,
    "sinh": sp.sinh,
    "cosh": sp.cosh,
    "tanh": sp.tanh,
    "exp": sp.exp,
    "sqrt": sp.sqrt,
    "abs": sp.Abs,
    "fabs": sp.Abs,
}

# Build transformations safely
_extra_transformations = []

for item in (implicit_multiplication_application, convert_xor):
    if isinstance(item, tuple):
        _extra_transformations.extend(item)
    else:
        _extra_transformations.append(item)

TRANSFORMATIONS = standard_transformations + tuple(_extra_transformations)

EXAMPLES = [
    "x^2 + y^2",
    "x^3*y^2 - 5*x*y + 7",
    "sin(x)*cos(y)",
    "exp(x*y)",
    "sqrt(x^2 + y^2)",
    "log(x^2 + y^2)",
    "x*y + e^(x+y)",
    "atan(x/y)",
]

# ------------------------------------------------------------------
# Helper functions
# ------------------------------------------------------------------
def pretty_str(expr):
    """
    Convert a SymPy expression into a nice readable string.
    """
    try:
        return sp.pretty(expr, use_unicode=True)
    except Exception:
        return str(expr)


def rationalize_floats(expr):
    """
    Try to convert floating point numbers inside the expression
    into exact rational numbers when possible.

    Example:
        0.5 -> 1/2
    """
    try:
        floats = list(expr.atoms(sp.Float))
    except Exception:
        return expr

    for f in floats:
        try:
            s = str(f)
            d = Decimal(s)

            if d.is_finite():
                exact_string = format(d.normalize(), "f")
                rational_value = sp.Rational(exact_string)
                expr = expr.xreplace({f: rational_value})
        except Exception:
            continue

    return expr


def parse_function(text):
    """
    Parse the user-entered function f(x,y).
    Supports:
        ^ for powers
        implicit multiplication like 2x, x y
        sin, cos, tan, exp, log, ln, sqrt, abs, pi, e
    """
    text = text.strip()

    if not text:
        raise ValueError("Please enter a function f(x,y).")

    expr = parse_expr(
        text,
        local_dict=LOCAL_DICT,
        transformations=TRANSFORMATIONS,
    )

    expr = rationalize_floats(expr)

    return expr


def parse_number(text, name):
    """
    Parse x0 or y0 value.

    Supports:
        integers: 2
        fractions: 1/2
        decimals: 0.5
        expressions: pi/2, sqrt(2), e/3
    """
    text = text.strip()

    if not text:
        return None

    # Try exact rational first: "1/2", "3", "0.25"
    try:
        return sp.Rational(text)
    except Exception:
        pass

    # Try Decimal for scientific notation like 1e-3
    try:
        d = Decimal(text)

        if d.is_finite():
            exact_string = format(d.normalize(), "f")
            return sp.Rational(exact_string)
    except Exception:
        pass

    # Try SymPy expression: pi/2, sqrt(2), e/3
    try:
        value = parse_expr(
            text,
            local_dict=LOCAL_DICT,
            transformations=TRANSFORMATIONS,
        )

        value = rationalize_floats(value)

        return value
    except Exception as exc:
        raise ValueError(f"Invalid value for {name}: {text}") from exc


def simplify_safe(expr):
    """
    Simplify expression safely.
    If simplification fails, return the original expression.
    """
    original = expr

    try:
        expr = sp.trigsimp(expr)
    except Exception:
        expr = original

    try:
        expr = sp.simplify(expr)
    except Exception:
        expr = original

    return expr


def numeric_value(expr, xv, yv):
    """
    Evaluate expression at x=xv, y=yv with high precision.
    """
    val = expr.subs({x: xv, y: yv})
    return sp.N(val, PRECISION)


def compute_output(expr_text, x_text, y_text):
    """
    Compute f, fx, fy, fxx, fyy, fxy, fyx.
    Also evaluate numerically if x0 and y0 are given.
    """
    # Parse function
    f = parse_function(expr_text)

    # First partial derivatives
    fx = sp.diff(f, x)
    fy = sp.diff(f, y)

    # Second partial derivatives
    fxx = sp.diff(fx, x)
    fyy = sp.diff(fy, y)
    fxy = sp.diff(fx, y)
    fyx = sp.diff(fy, x)

    # Simplify
    f = simplify_safe(f)
    fx = simplify_safe(fx)
    fy = simplify_safe(fy)
    fxx = simplify_safe(fxx)
    fyy = simplify_safe(fyy)
    fxy = simplify_safe(fxy)
    fyx = simplify_safe(fyx)

    out = StringIO()

    out.write("SYMBOLIC RESULTS\n")
    out.write("=" * 60 + "\n\n")

    def write_expr(name, expr):
        out.write(f"{name} =\n")
        out.write(pretty_str(expr))
        out.write("\n\n")

    write_expr("f(x, y)", f)
    write_expr("f_x", fx)
    write_expr("f_y", fy)
    write_expr("f_xx", fxx)
    write_expr("f_yy", fyy)
    write_expr("f_xy", fxy)
    write_expr("f_yx", fyx)

    # Hessian matrix
    hessian = sp.Matrix([[fxx, fxy], [fyx, fyy]])
    out.write("Hessian Matrix H =\n")
    out.write(pretty_str(hessian))
    out.write("\n\n")

    # Compare mixed partial derivatives
    try:
        mixed_difference = sp.simplify(fxy - fyx)

        if mixed_difference == 0:
            out.write("Result: f_xy and f_yx are equal after simplification.\n")
            out.write("This agrees with Clairaut's theorem when second partials are continuous.\n\n")
        else:
            out.write("Note: f_xy and f_yx did not simplify to the same expression.\n")
            out.write("f_xy - f_yx =\n")
            out.write(pretty_str(mixed_difference))
            out.write("\n\n")
    except Exception:
        out.write("Could not automatically compare f_xy and f_yx.\n\n")

    # Numerical evaluation if point is provided
    if x_text.strip() and y_text.strip():
        xv = parse_number(x_text, "x0")
        yv = parse_number(y_text, "y0")

        out.write("\nNUMERICAL EVALUATION\n")
        out.write("=" * 60 + "\n")
        out.write(f"Point: x0 = {pretty_str(xv)}, y0 = {pretty_str(yv)}\n")
        out.write(f"Precision: {PRECISION} digits\n\n")

        values = [
            ("f", f),
            ("f_x", fx),
            ("f_y", fy),
            ("f_xx", fxx),
            ("f_yy", fyy),
            ("f_xy", fxy),
            ("f_yx", fyx),
        ]

        for name, expr in values:
            val = numeric_value(expr, xv, yv)
            out.write(f"{name}(x0, y0) =\n")
            out.write(pretty_str(val))
            out.write("\n\n")
    else:
        out.write("Tip: Enter x0 and y0 if you want numerical values at a point.\n")

    return out.getvalue()


# ------------------------------------------------------------------
# GUI Application
# ------------------------------------------------------------------
class DerivativeCalculatorApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Higher Partial Derivative Calculator")
        self.root.geometry("1100x780")
        self.root.minsize(880, 600)

        self.build_ui()

    def build_ui(self):
        # Try to use a nicer theme if available
        style = ttk.Style()
        if "clam" in style.theme_names():
            style.theme_use("clam")

        main_frame = ttk.Frame(self.root, padding=12)
        main_frame.pack(fill=tk.BOTH, expand=True)

        # ------------------------------------------------------------
        # Function input
        # ------------------------------------------------------------
        function_frame = ttk.Frame(main_frame)
        function_frame.pack(fill=tk.X, pady=(0, 8))

        ttk.Label(
            function_frame,
            text="f(x, y) =",
            font=("Segoe UI", 11, "bold"),
        ).pack(side=tk.LEFT)

        self.expr_var = tk.StringVar(value="x^2*y + sin(y)")

        self.expr_entry = ttk.Entry(
            function_frame,
            textvariable=self.expr_var,
            font=("Consolas", 12),
        )

        self.expr_entry.pack(
            side=tk.LEFT,
            fill=tk.X,
            expand=True,
            padx=(8, 0),
        )

        self.expr_entry.bind("<Return>", lambda event: self.calculate())

        # ------------------------------------------------------------
        # Point input
        # ------------------------------------------------------------
        point_frame = ttk.Frame(main_frame)
        point_frame.pack(fill=tk.X, pady=(0, 8))

        ttk.Label(
            point_frame,
            text="x0 =",
            font=("Segoe UI", 11, "bold"),
        ).pack(side=tk.LEFT)

        self.x0_var = tk.StringVar(value="1")

        self.x0_entry = ttk.Entry(
            point_frame,
            textvariable=self.x0_var,
            width=22,
            font=("Consolas", 12),
        )

        self.x0_entry.pack(side=tk.LEFT, padx=(8, 20))
        self.x0_entry.bind("<Return>", lambda event: self.calculate())

        ttk.Label(
            point_frame,
            text="y0 =",
            font=("Segoe UI", 11, "bold"),
        ).pack(side=tk.LEFT)

        self.y0_var = tk.StringVar(value="pi/2")

        self.y0_entry = ttk.Entry(
            point_frame,
            textvariable=self.y0_var,
            width=22,
            font=("Consolas", 12),
        )

        self.y0_entry.pack(side=tk.LEFT, padx=(8, 0))
        self.y0_entry.bind("<Return>", lambda event: self.calculate())

        # ------------------------------------------------------------
        # Buttons and examples
        # ------------------------------------------------------------
        button_frame = ttk.Frame(main_frame)
        button_frame.pack(fill=tk.X, pady=(0, 8))

        self.calculate_button = ttk.Button(
            button_frame,
            text="Calculate Derivatives",
            command=self.calculate,
        )
        self.calculate_button.pack(side=tk.LEFT)

        ttk.Button(
            button_frame,
            text="Clear",
            command=self.clear_all,
        ).pack(side=tk.LEFT, padx=8)

        ttk.Button(
            button_frame,
            text="Copy Output",
            command=self.copy_output,
        ).pack(side=tk.LEFT, padx=8)

        self.example_combo = ttk.Combobox(
            button_frame,
            values=EXAMPLES,
            state="readonly",
            width=35,
        )

        self.example_combo.set("Load example...")
        self.example_combo.pack(side=tk.LEFT, padx=8)
        self.example_combo.bind("<<ComboboxSelected>>", self.load_example)

        # ------------------------------------------------------------
        # Status bar
        # ------------------------------------------------------------
        self.status_var = tk.StringVar(value="Ready")

        ttk.Label(
            main_frame,
            textvariable=self.status_var,
            foreground="#0a5d0a",
            font=("Segoe UI", 10),
        ).pack(anchor=tk.W)

        # ------------------------------------------------------------
        # Output window
        # ------------------------------------------------------------
        self.output = scrolledtext.ScrolledText(
            main_frame,
            wrap=tk.WORD,
            font=("Consolas", 11),
            undo=False,
        )

        self.output.pack(fill=tk.BOTH, expand=True, pady=(6, 0))
        self.output.configure(state="disabled")

        welcome_text = (
            "Enter a function f(x,y) and press Calculate Derivatives.\n\n"
            "Supported syntax:\n"
            "   x^2 + y^2\n"
            "   sin(x*y)\n"
            "   exp(x+y)\n"
            "   log(x^2 + y^2)\n"
            "   sqrt(x^2 + y^2)\n"
            "   x*y + e^(x+y)\n\n"
            "Variables: x, y\n"
            "Constants: pi, e\n"
            "Functions: sin, cos, tan, asin, acos, atan, sinh, cosh, tanh, exp, log, ln, sqrt, abs\n\n"
            "You can use ^ for powers.\n"
            "You can enter point values like 1, 0.5, 3/2, pi/2, sqrt(2).\n"
        )

        self.set_output(welcome_text)

    # ------------------------------------------------------------------
    # GUI actions
    # ------------------------------------------------------------------
    def set_output(self, text):
        self.output.configure(state="normal")
        self.output.delete("1.0", tk.END)
        self.output.insert(tk.END, text)
        self.output.configure(state="disabled")
        self.output.see(tk.END)

    def clear_all(self):
        self.expr_var.set("")
        self.x0_var.set("")
        self.y0_var.set("")
        self.example_combo.set("Load example...")
        self.status_var.set("Cleared")
        self.set_output("")

    def copy_output(self):
        self.output.configure(state="normal")
        text = self.output.get("1.0", tk.END)
        self.output.configure(state="disabled")

        self.root.clipboard_clear()
        self.root.clipboard_append(text)

        self.status_var.set("Output copied to clipboard.")

    def load_example(self, event=None):
        choice = self.example_combo.get()

        if choice and choice != "Load example...":
            self.expr_var.set(choice)
            self.calculate()

    def calculate(self):
        expr_text = self.expr_var.get().strip()
        x_text = self.x0_var.get().strip()
        y_text = self.y0_var.get().strip()

        if not expr_text:
            messagebox.showwarning(
                "Input Required",
                "Please enter a function f(x,y).",
            )
            return

        self.calculate_button.configure(state="disabled")
        self.status_var.set("Computing... Please wait.")

        thread = threading.Thread(
            target=self._calculation_worker,
            args=(expr_text, x_text, y_text),
            daemon=True,
        )

        thread.start()

    def _calculation_worker(self, expr_text, x_text, y_text):
        try:
            result = compute_output(expr_text, x_text, y_text)
            self.root.after(0, self._show_result, result)
        except Exception as e:
            self.root.after(0, self._show_error, str(e))

    def _show_result(self, result):
        self.set_output(result)
        self.calculate_button.configure(state="normal")
        self.status_var.set("Done.")

    def _show_error(self, error_message):
        self.calculate_button.configure(state="normal")
        self.status_var.set("Error.")

        messagebox.showerror(
            "Error",
            error_message,
        )


# ------------------------------------------------------------------
# Run app
# ------------------------------------------------------------------
def main():
    try:
        root = tk.Tk()
        app = DerivativeCalculatorApp(root)
        root.mainloop()
    except tk.TclError as e:
        # Fallback command-line mode if GUI cannot start
        print("GUI could not start:", e)
        print()
        print("Running in command-line mode.")
        print()

        expr_text = input("f(x,y) = ")
        x_text = input("x0 = ")
        y_text = input("y0 = ")

        try:
            result = compute_output(expr_text, x_text, y_text)
            print()
            print(result)
        except Exception as exc:
            print("Error:", exc)


if __name__ == "__main__":
    main()