import DataApp from './DataApp';
import * as Yup from 'yup';

const AlbumsApp = () => {
  const initialValues = {
    userId: '',
    title: ''
  };

  const validationSchema = Yup.object({
    userId: Yup.number().required('User ID is required'),
    title: Yup.string().required('Title is required')
  });

  const fields = [
    { name: 'userId', label: 'User ID', type: 'number' },
    { name: 'title', label: 'Title' }
  ];

  return (
    <DataApp
      endpoint="albums"
      initialValues={initialValues}
      validationSchema={validationSchema}
      fields={fields}
    />
  );
};

export default AlbumsApp;
