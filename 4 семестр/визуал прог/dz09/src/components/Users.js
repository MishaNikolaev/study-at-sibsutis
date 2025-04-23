import DataApp from './DataApp';
import * as Yup from 'yup';

const UsersApp = () => {
  const initialValues = {
    name: '',
    username: '',
    email: '',
    phone: '',
    website: ''
  };

  const validationSchema = Yup.object({
    name: Yup.string().required('Name is required'),
    username: Yup.string().required('Username is required'),
    email: Yup.string().email('Invalid email').required('Email is required'),
    phone: Yup.string(),
    website: Yup.string().url('Invalid URL')
  });

  const fields = [
    { name: 'name', label: 'Name' },
    { name: 'username', label: 'Username' },
    { name: 'email', label: 'Email', type: 'email' },
    { name: 'phone', label: 'Phone' },
    { name: 'website', label: 'Website' }
  ];

  return (
    <DataApp
      endpoint="users"
      initialValues={initialValues}
      validationSchema={validationSchema}
      fields={fields}
    />
  );
};

export default UsersApp;
